#include "ext.h"			// standard Max include, always required (except in Jitter)
#include "ext_obex.h"		// required for "new" style objects
#include "z_dsp.h"			// required for MSP objects
#include <julia.h>

JULIA_DEFINE_FAST_TLS()


// struct to represent the object's state
typedef struct _simplemsp {
	t_pxobject		ob;			// the object itself (t_pxobject in MSP instead of t_object)
	double			offset; 	// the value of a property of our object
} t_dspnode;


// method prototypes
void *simplemsp_new(t_symbol *s, long argc, t_atom *argv);
void simplemsp_free(t_dspnode *x);
void simplemsp_assist(t_dspnode *x, void *b, long m, long a, char *s);
void simplemsp_float(t_dspnode *x, double f);
void simplemsp_dsp64(t_dspnode *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags);
void simplemsp_perform64(t_dspnode *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam);


// global class pointer variable
static t_class *simplemsp_class = NULL;


//***********************************************************************************************

void ext_main(void *r)
{
	// object initialization, note the use of dsp_free for the freemethod, which is required
	// unless you need to free allocated memory, in which case you should call dsp_free from
	// your custom free function.

	t_class *c = class_new("dspnode~", (method)simplemsp_new, (method)dsp_free, (long)sizeof(t_dspnode), 0L, A_GIMME, 0);

	class_addmethod(c, (method)simplemsp_float,		"float",	A_FLOAT, 0);
	class_addmethod(c, (method)simplemsp_dsp64,		"dsp64",	A_CANT, 0);
	class_addmethod(c, (method)simplemsp_assist,	"assist",	A_CANT, 0);

	class_dspinit(c);
	class_register(CLASS_BOX, c);
	simplemsp_class = c;
}


void *simplemsp_new(t_symbol *s, long argc, t_atom *argv)
{
	t_dspnode *x = (t_dspnode *)object_alloc(simplemsp_class);

	if (x) {
        dsp_setup((t_pxobject *)x, 2);
        outlet_new(x, "signal");
        outlet_new(x, "signal");
        x->offset = 0.0;
	}
	return (x);
}


// NOT CALLED!, we use dsp_free for a generic free function
void simplemsp_free(t_dspnode *x)
{
	;
}


void simplemsp_assist(t_dspnode *x, void *b, long m, long a, char *s)
{
	if (m == ASSIST_INLET) { //inlet
		sprintf(s, "I am inlet %ld", a);
	}
	else {	// outlet
		sprintf(s, "I am outlet %ld", a);
	}
}


void simplemsp_float(t_dspnode *x, double f)
{
	x->offset = f;
}


// registers a function for the signal chain in Max
void simplemsp_dsp64(t_dspnode *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags)
{
	post("my sample rate is: %f", samplerate);

    jl_init(); // initialize julia, this in itself does not break anything
	object_method(dsp64, gensym("dsp_add64"), x, simplemsp_perform64, 0, NULL);
    jl_atexit_hook(0);
}


// this is the 64-bit perform method audio vectors
void simplemsp_perform64(t_dspnode *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam)
{
    // Getting the left and right inlets/outlets
    t_double *inLeft = ins[0];
    t_double *outLeft = outs[0];
    t_double *inRight = ins[1];
    t_double *outRight = outs[1];
    int n = sampleframes;
    
    // this chunk of code currently crashes max
            
    //================= Julia API ================
    
    // load julia code
    (void)jl_eval_string("include(\"dsp_source.jl\")");
    
    // get module
    (void)jl_eval_string("using .dsp_source");
    jl_module_t* juliaDSP = (jl_module_t*)jl_eval_string("dsp");
    
    // get dsp function
    jl_function_t *func = jl_get_function(juliaDSP, "dsp");

    // julia float64 array type
    jl_value_t* array_type = jl_apply_array_type((jl_value_t*)jl_float64_type, 1);

    // connecting julia array to the left and right C arrays
    jl_array_t *left = jl_ptr_to_array_1d(array_type, inLeft, n, 0);
    jl_array_t *right = jl_ptr_to_array_1d(array_type, inRight, n, 0);

    // boxing the samplerate
    jl_value_t *sampleRate = jl_box_uint64(n);
    
    // call the dsp julia function, passing through the left/right channels as arguments
    jl_call3(func, (jl_value_t*)left, (jl_value_t*)right, sampleRate);
    
//    while (n--)
//        *outLeft++ = *inLeft++;
//        *outRight++ = *inRight++;
}

