#include "ext.h"			// standard Max include, always required (except in Jitter)
#include "ext_obex.h"		// required for "new" style objects
#include "z_dsp.h"			// required for MSP objects


double gain(double gain_inp, double input) {
     return gain_inp+input;
}

typedef double (*func)(double, double);


// struct to represent the object's state
typedef struct _dspnode {
	t_pxobject		ob;			// the object itself (t_pxobject in MSP instead of t_object)
    func       funcPtr;
    double			offset;
} t_dspnode;


// method prototypes
void *dspnode_new(t_symbol *s, long argc, t_atom *argv);
void dspnode_free(t_dspnode *x);
void dspnode_assist(t_dspnode *x, void *b, long m, long a, char *s);
void dspnode_float(t_dspnode *x, double f);
void dspnode_dsp64(t_dspnode *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags);
void dspnode_perform64(t_dspnode *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam);


// global class pointer variable
static t_class *dspnode_class = NULL;


//***********************************************************************************************

void ext_main(void *r)
{
	// object initialization, note the use of dsp_free for the freemethod, which is required
	// unless you need to free allocated memory, in which case you should call dsp_free from
	// your custom free function.

	t_class *c = class_new("dspnode~", (method)dspnode_new, (method)dsp_free, (long)sizeof(t_dspnode), 0L, A_GIMME, 0);

	class_addmethod(c, (method)dspnode_float,		"float",	A_FLOAT, 0);
	class_addmethod(c, (method)dspnode_dsp64,		"dsp64",	A_CANT, 0);
	class_addmethod(c, (method)dspnode_assist,	    "assist",	A_CANT, 0);
//    class_addmethod(c, (method)gain,                "gain",     A_CANT, 0);

	class_dspinit(c);
	class_register(CLASS_BOX, c);
	dspnode_class = c;
}


void *dspnode_new(t_symbol *s, long argc, t_atom *argv)
{
	t_dspnode *x = (t_dspnode *)object_alloc(dspnode_class);

	if (x) {
        dsp_setup((t_pxobject *)x, 2);
        outlet_new(x, "signal");
        outlet_new(x, "signal");
        x->offset = 0.0;
        x->funcPtr = gain;
	}
	return (x);
}


// NOT CALLED!, we use dsp_free for a generic free function
void dspnode_free(t_dspnode *x)
{
	;
}


void dspnode_assist(t_dspnode *x, void *b, long m, long a, char *s)
{
	if (m == ASSIST_INLET) { //inlet
		sprintf(s, "I am inlet %ld", a);
	}
	else {	// outlet
		sprintf(s, "I am outlet %ld", a);
	}
}


void dspnode_float(t_dspnode *x, double f)
{
	x->offset = f;
}


// registers a function for the signal chain in Max
void dspnode_dsp64(t_dspnode *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags)
{
	post("my sample rate is: %f", samplerate);

	object_method(dsp64, gensym("dsp_add64"), x, dspnode_perform64, 0, NULL);
}


// this is the 64-bit perform method audio vectors
void dspnode_perform64(t_dspnode *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam)
{
    // Getting the left and right inlets/outlets
    t_double *inLeft = ins[0];
    t_double *outLeft = outs[0];
    t_double *inRight = ins[1];
    t_double *outRight = outs[1];
    int n = sampleframes;
    double gain = 6.0;
    
    while(n--) {
        *outLeft++ = (x->funcPtr)(gain, *inLeft++);
        *outLeft++ = (x->funcPtr)(gain, *inLeft++);
    }

}

