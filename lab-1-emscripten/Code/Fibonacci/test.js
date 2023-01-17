
var test = Module.onRuntimeInitialized = () => {
    var time = "";
    for (var i = 0; i < 100; i++){
        var t0 = performance.now();
        var res = Module.ccall('getFib', 'number');
        var t1 = performance.now();
        asmTime = (t1 - t0) / 1000;
        // console.log(res);
        time += asmTime + '<br>';
        console.log("Time", asmTime);
    }
    body = document.body
    body.innerHTML = time
}
