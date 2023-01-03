const utils = require("./util");
const fs = require("fs");

try {
    const hyp = fs.readFileSync("./hyp.txt", "utf8");
    const ref1 = fs.readFileSync("./ref1.txt", "utf8");
    const ref2 = fs.readFileSync("./ref2.txt", "utf8");
    const _hyp = utils.tokeniser(hyp);

    let E = Infinity;
    const refs = [ref1, ref2];
    for (const ref of refs) {
        const _ref = utils.tokeniser(ref);
        console.log(_hyp + "\n" + _ref + "\n");

        let e = 0;
        let h = [..._hyp];

        while (true) {
            // find all possible shifts
            const shifts = utils.findAllShiftsInDocs(_hyp, _ref);
            let sh = null,
                min_h,
                edit_dist = utils.minEditDistance(h, _ref);
            const cur_dist = edit_dist;

            for (const shift of shifts) {
                //apply shift to doc and find minEditDistance
                let _h = utils.shiftDoc([...h], shift);
                let dist = utils.minEditDistance(_h, _ref) + 1;

                // If it's less than previous , save it,  accept the shift that yields minimum edit-distance
                if (dist < edit_dist) {
                    edit_dist = dist;
                    sh = shift;
                    min_h = _h;
                }
            }

            // if any shift decreases edit-distance, go for next interation otherwise stop
            if (edit_dist < cur_dist) {
                h = min_h;
                e++;
            } else break;
        }
        console.log("Final hypothesis: " + utils.stringFromTokens(h));

        e += utils.minEditDistance(h, _ref);
        if (e < E) E = e;
    }

    let avgRefLength = 0;
    for(const ref of refs) avgRefLength += ref.length;
    avgRefLength /= refs.length;

    console.log("Min edit including shifts: " + E);
    console.log("TER: " + ((E / avgRefLength) * 100).toFixed(2) + " %");
} catch (err) {
    console.error(err);
}

// const hyp =
//     "this week the saudis denied information published in the new york times";
// const ref =
//     "saudi arabia denied this week information published in the american new york times";
