import * as asm from "../../wasm/asm.js"

export function listenInput() {
    $("#app-holder").on('input propertychange', '#mie input', function() {
        // collect page input
        var csr = {};
        csr["hex"] = $("#mie").find(".csr-input-hex").val();
        csr["bin"] = $("#mie").find(".csr-input-bin").val();
        $("#mie").find(".csr-input-field").each(function() {
            csr[$(this).attr("field")] = $(this).val();
        });

        // pass to wasm
        if ($(this).hasClass("csr-input-field")) {
            csr = asm.Module.mie_handler(csr, asm.Module.HANDLE.CSR_FIELD_CHANGE);
        } else if ($(this).hasClass("csr-input-hex")) {
            csr = asm.Module.mie_handler(csr, asm.Module.HANDLE.CSR_HEX_CHANGE);
        } else if ($(this).hasClass("csr-input-bin")) {
            csr = asm.Module.mie_handler(csr, asm.Module.HANDLE.CSR_BIN_CHANGE);
        } else {
            console.log("Incorrect mie request");
        }

        // render output
        $("#mie").find(".csr-input-hex").val(csr["hex"]);
        $("#mie").find(".csr-input-bin").val(csr["bin"]);
        Object.keys(csr).forEach((key, index) => {
            $("#mie input[field="+key+"]").val(csr[key]);
        })
    });
}