import * as asm from "../../wasm/asm.js"

export function listenInput() {
    $("#app-holder").on('input propertychange', '#sie input', function() {
        // collect page input
        var csr = {};
        csr["hex"] = $("#sie").find(".csr-input-hex").val();
        csr["bin"] = $("#sie").find(".csr-input-bin").val();
        $("#sie").find(".csr-input-field").each(function() {
            csr[$(this).attr("field")] = $(this).val();
        });

        // pass to wasm
        if ($(this).hasClass("csr-input-field")) {
            csr = asm.Module.sie_handler(csr, asm.Module.HANDLE.CSR_FIELD_CHANGE);
        } else if ($(this).hasClass("csr-input-hex")) {
            csr = asm.Module.sie_handler(csr, asm.Module.HANDLE.CSR_HEX_CHANGE);
        } else if ($(this).hasClass("csr-input-bin")) {
            csr = asm.Module.sie_handler(csr, asm.Module.HANDLE.CSR_BIN_CHANGE);
        } else {
            console.log("Incorrect sie request");
        }

        // render output
        $("#sie").find(".csr-input-hex").val(csr["hex"]);
        $("#sie").find(".csr-input-bin").val(csr["bin"]);
        Object.keys(csr).forEach((key, index) => {
            $("#sie input[field="+key+"]").val(csr[key]);
        })
    });
}