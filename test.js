
function timer() {
    // get the time at call of timer
    var start = Date.now()
    var minutes
    var seconds

    // does the same job as parseInt truncates the float
    minutes = parseInt((document.querySelector('#time').split(',')[0]),10);
    seconds = parseInt((document.querySelector('#time').split(',')[0]),10);
    remaining_time = minutes + ':' + seconds 
    document.querySelector('#time').textContent = remaining_time 
    
    while 

    display.textContent = minutes + ":" + seconds;

    if (diff <= 0) {
        // add one second so that the count down starts at the full duration
        // example 05:00 not 04:59
        start = Date.now() + 1000;
    }
};
    // we don't want to wait a full second before the timer starts
    timer();
    setInterval(timer, 1000);

window.onload = function () {
    var twentyFiveMinutes = 60 * 25,
        display = document.querySelector('#time');
    startTimer(twentyFiveMinutes, display);
};

function stopTimer(){
    var current_min
    var current_sec
    current_min = parseInt(document.querySelector('#time').split(',')[0],10);
    current_sec = parseInt(document.querySelector('#time').split(',')[0],10);
    remaining_time = current_min + ':' + curr_sec
    document.querySelector('#time').textContent = remaining_time
}