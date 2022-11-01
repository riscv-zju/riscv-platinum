import * as asm from "../../wasm/asm.js"

export function listenInput() {
    $("#app-holder").on('input propertychange', '#mstatus input', function() {
        // collect page input
        var csr = {};
        csr["hex"] = $("#mstatus").find(".csr-input-hex").val();
        csr["bin"] = $("#mstatus").find(".csr-input-bin").val();
        $("#mstatus").find(".csr-input-field").each(function() {
            csr[$(this).attr("field")] = $(this).val();
        });

        // pass to wasm
        if ($(this).hasClass("csr-input-field")) {
            csr = asm.Module.mstatus_handler(csr, asm.Module.HANDLE.CSR_FIELD_CHANGE);
        } else if ($(this).hasClass("csr-input-hex")) {
            csr = asm.Module.mstatus_handler(csr, asm.Module.HANDLE.CSR_HEX_CHANGE);
        } else if ($(this).hasClass("csr-input-bin")) {
            csr = asm.Module.mstatus_handler(csr, asm.Module.HANDLE.CSR_BIN_CHANGE);
        } else {
            console.log("Incorrect mstatus request");
        }

        // render output
        $("#mstatus").find(".csr-input-hex").val(csr["hex"]);
        $("#mstatus").find(".csr-input-bin").val(csr["bin"]);
        Object.keys(csr).forEach((key, index) => {
            $("#mstatus input[field="+key+"]").val(csr[key]);
        })
    });
}