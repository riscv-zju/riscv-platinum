// import * as asm from "../../wasm/asm.js"

export function listenInput() {
    $("#app-holder").on('input propertychange', '#mstatus input', function() {
        // wasm version has bug :(
        // var csr1 = { sd  : "1", rev0: "0", mbe : "0", sbe : "0", sxl : "0",
        //           uxl : "0", rev1: "0", tsr : "0", tw  : "0", tvm : "0",
        //           mxr : "0", sum : "0", mprv: "0", xs  : "0", fs  : "0",
        //           mpp : "0", vs  : "0", spp : "0", mpie: "0", ube : "0",
        //           spie: "0", rev2: "0", mie : "0", rev3: "0", sie : "0",
        //           rev4: "0"
        //         };
        // console.log(asm.Module.dump_csr_mastatus(csr));
        
        if ($(this).hasClass("csr-input-field")) {
            var csr = {};
            $("#mstatus").find(".csr-input-field").each(function() {
                csr[$(this).attr("field")] = $(this).val()
            });

            var high = 0 | 
            parseInt(csr.sd, 2) << 31 |
            parseInt(csr.rev0, 2) << 6 |
            parseInt(csr.mbe, 2) << 5 |
            parseInt(csr.sbe, 2) << 4 |
            parseInt(csr.sxl, 2) << 2 |
            parseInt(csr.uxl, 2) << 0;
            high = high >>> 0;

            var low = 0 | 
            parseInt(csr.rev1, 2) << 23 |
            parseInt(csr.tsr, 2) << 22 |
            parseInt(csr.tw, 2) << 21 |
            parseInt(csr.tvm, 2) << 20 |
            parseInt(csr.mxr, 2) << 19 |
            parseInt(csr.sum, 2) << 18 |
            parseInt(csr.mprv, 2) << 17 |
            parseInt(csr.xs, 2) << 15 |
            parseInt(csr.fs, 2) << 13 |
            parseInt(csr.mpp, 2) << 11 |
            parseInt(csr.vs, 2) << 9 |
            parseInt(csr.spp, 2) << 8 |
            parseInt(csr.mpie, 2) << 7 |
            parseInt(csr.ube, 2) << 6 |
            parseInt(csr.spie, 2) << 5 |
            parseInt(csr.rev2, 2) << 4 |
            parseInt(csr.mie, 2) << 3 |
            parseInt(csr.rev3, 2) << 2 |
            parseInt(csr.sie, 2) << 1 |
            parseInt(csr.rev4, 2) << 0;
            low = low >>> 0;

            $("#mstatus").find(".csr-input-hex").val(
                high.toString(16).padStart(8, "0") + low.toString(16).padStart(8, "0"));
            $("#mstatus").find(".csr-input-bin").val(
                high.toString(2).padStart(32, "0") + low.toString(2).padStart(32, "0"));
        } else if ($(this).hasClass("csr-input-hex")) {
            var raw = $(this).val().padStart(16, "0")
            var high = parseInt(raw.substr(0, 8), 16) >>> 0;
            var low = parseInt(raw.substr(8, 8), 16) >>> 0;

            var csr = {}
            csr.sd = (high >>> 31) & 1;
            csr.rev0 = (high >>> 6) & 255;
            csr.mbe = (high >>> 5) & 1;
            csr.sbe = (high >>> 4) & 1;
            csr.sxl = (high >>> 2) & 3;
            csr.uxl = (high >>> 0) & 3;
            csr.rev1 = (low >> 23) & 511;
            csr.tsr = (low >> 22) & 1;
            csr.tw = (low >> 21) & 1;
            csr.tvm = (low >> 20) & 1;
            csr.mxr = (low >> 19) & 1;
            csr.sum = (low >> 18) & 1;
            csr.mprv = (low >> 17) & 1;
            csr.xs = (low >> 15) & 3;
            csr.fs = (low >> 13) & 3;
            csr.mpp = (low >> 11) & 3;
            csr.vs = (low >> 9) & 3;
            csr.spp = (low >> 8) & 1;
            csr.mpie = (low >> 7) & 1;
            csr.ube = (low >> 6) & 1;
            csr.spie = (low >> 5) & 1;
            csr.rev2 = (low >> 4) & 1;
            csr.mie = (low >> 3) & 1;
            csr.rev3 = (low >> 2) & 1;
            csr.sie = (low >> 1) & 1;
            csr.rev4 = (low >> 0) & 1;

            Object.keys(csr).forEach((key, index) => {
                $("#mstatus input[field="+key+"]").val(csr[key].toString(2))
            })
            $("#mstatus").find(".csr-input-bin").val(
                high.toString(2).padStart(32, "0") + low.toString(2).padStart(32, "0"));
        } else if ($(this).hasClass("csr-input-bin")) {
            var raw = $(this).val().padStart(64, "0")
            var high = parseInt(raw.substr(0, 32), 2) >>> 0;
            var low = parseInt(raw.substr(32, 32), 2) >>> 0;

            var csr = {}
            csr.sd = (high >>> 31) & 1;
            csr.rev0 = (high >>> 6) & 255;
            csr.mbe = (high >>> 5) & 1;
            csr.sbe = (high >>> 4) & 1;
            csr.sxl = (high >>> 2) & 3;
            csr.uxl = (high >>> 0) & 3;
            csr.rev1 = (low >> 23) & 511;
            csr.tsr = (low >> 22) & 1;
            csr.tw = (low >> 21) & 1;
            csr.tvm = (low >> 20) & 1;
            csr.mxr = (low >> 19) & 1;
            csr.sum = (low >> 18) & 1;
            csr.mprv = (low >> 17) & 1;
            csr.xs = (low >> 15) & 3;
            csr.fs = (low >> 13) & 3;
            csr.mpp = (low >> 11) & 3;
            csr.vs = (low >> 9) & 3;
            csr.spp = (low >> 8) & 1;
            csr.mpie = (low >> 7) & 1;
            csr.ube = (low >> 6) & 1;
            csr.spie = (low >> 5) & 1;
            csr.rev2 = (low >> 4) & 1;
            csr.mie = (low >> 3) & 1;
            csr.rev3 = (low >> 2) & 1;
            csr.sie = (low >> 1) & 1;
            csr.rev4 = (low >> 0) & 1;

            Object.keys(csr).forEach((key, index) => {
                $("#mstatus input[field="+key+"]").val(csr[key].toString(2))
            })
            $("#mstatus").find(".csr-input-hex").val(
                high.toString(16).padStart(8, "0") + low.toString(16).padStart(8, "0"));
        } else {
            console.log("Incorrect mstatus request");
        }
    });
}