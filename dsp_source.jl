module dsp_source
    export dsp
    function dsp(left, right, sampleRate)
        left, right = right, left
    end
end