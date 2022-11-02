import * as mstatus from "./csr-visual/mstatus/app.js"
import * as sstatus from "./csr-visual/sstatus/app.js"
import * as mie from "./csr-visual/mie/app.js"
import * as medeleg from "./csr-visual/medeleg/app.js"

export function loadAppResource(path, icon=true) {
    fetch(path+"/ui.html")
    .then(response => response.text())
    .then(text => {
        // console.log(text);
        $("#app-holder").append(text);
        jQuery(".draggable-window").draggable();
        jQuery(".resizable .inner").resizable();
    });

    if (icon) {
        fetch(path+"/icon.html")
        .then(response => response.text())
        .then(text => {
            // console.log(text);
            $("#icon-holder").append(text);
            jQuery(".draggable-icon").draggable({});
        });
    }
}


export function registerApp() {
    mstatus.listenInput()
    sstatus.listenInput()
    mie.listenInput()
    medeleg.listenInput()
}