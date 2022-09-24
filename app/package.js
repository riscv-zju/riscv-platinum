import * as mstatus from "./csr-visual/mstatus/app.js"

export function loadAppResource(path) {
    fetch(path+"/ui.html")
    .then(response => response.text())
    .then(text => {
        // console.log(text);
        $("#app-holder").append(text);
        jQuery(".draggable-window").draggable();
        jQuery(".resizable .inner").resizable();
    });

    fetch(path+"/icon.html")
    .then(response => response.text())
    .then(text => {
        // console.log(text);
        $("#icon-holder").append(text);
        jQuery(".draggable-icon").draggable({});
    });
}


export function registerApp() {
    mstatus.listenInput()
}