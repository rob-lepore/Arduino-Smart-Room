const ctx = document.getElementById('myChart');

const chart = new Chart(ctx, {
    type: "line",
    data: {
        labels: [],
        datasets: [
            {
                label: "Lamp State",
                data: [],
                backgroundColor: ["rgba(54, 162, 235, 0.2)"],
                borderColor: ["rgba(54, 162, 235, 1)"],
                borderWidth: 1,
                pointStyle:false,

            },
        ],
    },
    options: {
        scales: {
            x: {
                title: {
                    display: true,
                    text: 'Time'
                }
            },
            y: {
                min: 0,
                max: 1,
                ticks: {
                    callback: (v,i,t) => {
                        return v == 1 ? "On" : "Off";
                    },
                    stepSize: 1
                }
            }
        }
    },
});


let values = [];
let timestamps = [];

function getValues() {
    fetch("/getValues").then(res => res.json()).then(json => {
        document.querySelector("#lightValue").textContent = json.level;
        document.querySelector("#movementValue").textContent = json.movement == 1 ? "Detected" : "Not detected";
        document.querySelector("#fromSerial").textContent = json.fromSerial;


        values.push(json.fromSerial == "Lamp On" ? 1 : 0);
        timestamps.push(getTime());

        if (values.length > 100) {
            values.splice(0, 1);
            timestamps.splice(0, 1);
        }

        chart.data.datasets[0].data = values;
        chart.data.labels = timestamps;
        chart.update("none");
    })
}
getValues();
setInterval(getValues, 1000);


function getTime() {
    return new Date().getHours() + ":" + new Date().getMinutes() + ":" + new Date().getSeconds();
}




let remoteOn = false;
function toggleRemote() {
    let btn = document.querySelector("#remoteBtn");
    btn.classList.toggle("btn-primary");
    btn.classList.toggle("btn-secondary");
    btn.textContent = remoteOn ? "Turn Remote Control On" : "Turn Remote Control Off";
    remoteOn = !remoteOn;
    document.querySelector("#controls").classList.toggle("d-none");

    fetch("/setSerialControl?to=" + (remoteOn ? "1" : "0")).then(res => res.json()).then(json => {
        console.log(json);
    })
}

let lampState = false;
function setLamp(on) {
    if (on != lampState) {
        document.querySelector("#onBtn").classList.toggle("btn-dark")
        document.querySelector("#onBtn").classList.toggle("btn-light")
        document.querySelector("#offBtn").classList.toggle("btn-dark")
        document.querySelector("#offBtn").classList.toggle("btn-light")
        lampState = !lampState;

        fetch("/setLamp?to=" + (lampState ? "1" : "0")).then(res => res.json()).then(json => {
            console.log(json);
        })
    }

}


function setBlinds() {
    let val = document.querySelector("#rangeinput").value;
    fetch("/setBlinds?to=" + val).then(res => res.json()).then(json => {
        console.log(json);
    })
}

