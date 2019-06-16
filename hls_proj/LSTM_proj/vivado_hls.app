<project xmlns="com.autoesl.autopilot.project" name="LSTM_proj" top="lstm">
    <files>
        <file name="../../../c_code/top/lstm_test.cpp" sc="0" tb="1" cflags=" -I../../.  -std=c++0x"/>
        <file name="../c_code/ElemWiseSigmoid/ElemWiseSigmoid.cpp" sc="0" tb="false" cflags=""/>
        <file name="../c_code/ElemWiseTanh/ElemWiseTanh.cpp" sc="0" tb="false" cflags=""/>
        <file name="../c_code/ElemWiseVecAdd/ElemWiseVecAdd.cpp" sc="0" tb="false" cflags=""/>
        <file name="../c_code/ElemWiseVecMul/ElemWiseVecMul.cpp" sc="0" tb="false" cflags=""/>
        <file name="../data/tensorflow_data/Whc.txt" sc="0" tb="false" cflags=""/>
        <file name="../data/tensorflow_data/Whf.txt" sc="0" tb="false" cflags=""/>
        <file name="../data/tensorflow_data/Whi.txt" sc="0" tb="false" cflags=""/>
        <file name="../data/tensorflow_data/Who.txt" sc="0" tb="false" cflags=""/>
        <file name="../data/tensorflow_data/Wxc.txt" sc="0" tb="false" cflags=""/>
        <file name="../data/tensorflow_data/Wxf.txt" sc="0" tb="false" cflags=""/>
        <file name="../data/tensorflow_data/Wxi.txt" sc="0" tb="false" cflags=""/>
        <file name="../data/tensorflow_data/Wxo.txt" sc="0" tb="false" cflags=""/>
        <file name="../data/tensorflow_data/Wy.txt" sc="0" tb="false" cflags=""/>
        <file name="../data/tensorflow_data/bc.txt" sc="0" tb="false" cflags=""/>
        <file name="../data/tensorflow_data/bf.txt" sc="0" tb="false" cflags=""/>
        <file name="../data/tensorflow_data/bi.txt" sc="0" tb="false" cflags=""/>
        <file name="../data/tensorflow_data/bo.txt" sc="0" tb="false" cflags=""/>
        <file name="../data/tensorflow_data/by.txt" sc="0" tb="false" cflags=""/>
        <file name="../data/tensorflow_data/logits_series.txt" sc="0" tb="false" cflags=""/>
        <file name="../c_code/top/lstm.cpp" sc="0" tb="false" cflags=""/>
        <file name="../c_code/matrix_vector_mult/mv_input.cpp" sc="0" tb="false" cflags=""/>
        <file name="../c_code/matrix_vector_mult/mv_output.cpp" sc="0" tb="false" cflags=""/>
        <file name="../c_code/matrix_vector_mult/mv_state.cpp" sc="0" tb="false" cflags=""/>
        <file name="../data/tensorflow_data/predictions_series.txt" sc="0" tb="false" cflags=""/>
        <file name="../data/tensorflow_data/states_series.txt" sc="0" tb="false" cflags=""/>
    </files>
    <includePaths/>
    <libraryPaths/>
    <Simulation>
        <SimFlow name="csim" csimMode="0" lastCsimMode="0" compiler="true"/>
    </Simulation>
    <solutions xmlns="">
        <solution name="solution1" status="active"/>
    </solutions>
</project>

