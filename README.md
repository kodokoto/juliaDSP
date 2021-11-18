# JuliaDSP
 
Max External object that allows you to write DSP in Julia, using Julias C API to call an external Julia function. I.e:
```julia 
module dsp_source
    export dsp
    function dsp(left, right, sampleRate)
        # write your dsp code here
    end
end
```

# Current state
Builds but crashes

# Isssues
- Adding a `jl_` function call from Julia's C API crashes Max when you add the mxo to the project. For example simply adding this:
  ```c
  (void)jl_eval_string("print(4)");
  ```
    crashes Max when you call it inside of 
  `simplemsp_perform64()`
- Not sure about how Julia's Garbage Collector is going to manage the 64bit float arrays from C
