import * as asm from "../../wasm/asm.js"

export function listenInput() {
    $("#app-holder").on('input propertychange', '#medeleg input', function() {
        // collect page input
        var csr = {};
        csr["hex"] = $("#medeleg").find(".csr-input-hex").val();
        csr["bin"] = $("#medeleg").find(".csr-input-bin").val();
        $("#medeleg").find(".csr-input-field").each(function() {
            csr[$(this).attr("field")] = $(this).val();
        });

        // pass to wasm
        if ($(this).hasClass("csr-input-field")) {
            csr = asm.Module.medeleg_handler(csr, asm.Module.HANDLE.CSR_FIELD_CHANGE);
        } else if ($(this).hasClass("csr-input-hex")) {
            csr = asm.Module.medeleg_handler(csr, asm.Module.HANDLE.CSR_HEX_CHANGE);
        } else if ($(this).hasClass("csr-input-bin")) {
            csr = asm.Module.medeleg_handler(csr, asm.Module.HANDLE.CSR_BIN_CHANGE);
        } else {
            console.log("Incorrect medeleg request");
        }

        // render output
        $("#medeleg").find(".csr-input-hex").val(csr["hex"]);
        $("#medeleg").find(".csr-input-bin").val(csr["bin"]);
        Object.keys(csr).forEach((key, index) => {
            $("#medeleg input[field="+key+"]").val(csr[key]);
        })
    });
}