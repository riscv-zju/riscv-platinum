import * as asm from "../../wasm/asm.js"

export function listenInput() {
    $("#app-holder").on('input propertychange', '#sstatus input', function() {
        // collect page input
        var csr = {};
        csr["hex"] = $("#sstatus").find(".csr-input-hex").val();
        csr["bin"] = $("#sstatus").find(".csr-input-bin").val();
        $("#sstatus").find(".csr-input-field").each(function() {
            csr[$(this).attr("field")] = $(this).val();
        });

        // pass to wasm
        if ($(this).hasClass("csr-input-field")) {
            csr = asm.Module.sstatus_handler(csr, asm.Module.HANDLE.CSR_FIELD_CHANGE);
        } else if ($(this).hasClass("csr-input-hex")) {
            csr = asm.Module.sstatus_handler(csr, asm.Module.HANDLE.CSR_HEX_CHANGE);
        } else if ($(this).hasClass("csr-input-bin")) {
            csr = asm.Module.sstatus_handler(csr, asm.Module.HANDLE.CSR_BIN_CHANGE);
        } else {
            console.log("Incorrect sstatus request");
        }

        // render output
        $("#sstatus").find(".csr-input-hex").val(csr["hex"]);
        $("#sstatus").find(".csr-input-bin").val(csr["bin"]);
        Object.keys(csr).forEach((key, index) => {
            $("#sstatus input[field="+key+"]").val(csr[key]);
        })
    });
}