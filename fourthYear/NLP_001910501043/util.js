// transform text to lowercase, removes fullstops or punctuations
//then generates tokens by splitting by white space. returns list of tokens.
function tokeniser(text) {
    // replace newline '\n' with space
    let regex = /[\n]/g;
    text = text.replace(regex, " ");
    //remove all punctuation including fullstops
    regex = /[.,\/#!'"$?%\^&\*;:{}=\-_`~()]/g;
    text = text.replace(regex, "");

    //trim and split on white space
    return text.trim().split(" ");
}

function stringFromTokens(tokens) {
    // join tokens with space:
    return tokens.join(" ");
}

// Both args are [list of tokens],
function findAllShiftsInDocs(source, dest) {
    // initialise table
    let dp = Array.from(
        Array(source.length + 1),
        () => new Array(dest.length + 1)
    );
    for (let i = 0; i <= source.length; i++) {
        for (let j = 0; j <= dest.length; j++) {
            dp[i][j] = 0;
        }
    }

    for (let i = 1; i <= source.length; i++) {
        for (let j = 1; j <= dest.length; j++) {
            if (source[i - 1] == dest[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1] + 1;
            } else {
                dp[i][j] = 0;
            }
        }
    }

    let res = [];
    for (let i = dp.length - 1; i >= 0; i--) {
        for (let j = dp[0].length - 1; j >= 0; j--) {
            // consider phrase sequence of more than 2 words
            if (i != j && dp[i][j] >= 2) {
                let ci = i,
                    cj = j;
                let shift = {
                    length: dp[i][j],
                    position: i - dp[i][j],
                    insertAt: 0,
                };

                // assign zero so that doen's count in next iteration
                while (dp[ci][cj] > 0) {
                    dp[ci][cj] = 0;
                    ci--;
                    cj--;
                }

                // find all occurence of two surrounding words of the phrase sequence (of dest) in source
                cj = j - shift.length - 1;
                ci = -1;
                if (cj >= 0)
                    while ((ci = source.indexOf(dest[cj], ci + 1)) != -1) {
                        shift.insertAt = ci;
                        res.push(shift);
                    }

                ci = -1;
                cj = j;
                if (cj < dest.length)
                    while ((ci = source.indexOf(dest[cj], ci + 1)) != -1) {
                        shift.insertAt = ci;
                        res.push(shift);
                    }
            }
        }
    }
    return res;
}

// doc is list of token, returns modified list of token
function shiftDoc(doc, shift) {
    const deletedElements = doc.splice(shift.position, shift.length);

    let index = -1;
    if (shift.insertAt > shift.position) index = shift.insertAt - shift.length;
    else index = shift.insertAt;

    doc.splice(index, 0, ...deletedElements);
    return doc;
}

// both args are list of tokens, returns the min edit distance at word level.
function minEditDistance(doc1, doc2) {
    // initialise table
    let dp = Array.from(
        Array(doc1.length + 1),
        () => new Array(doc2.length + 1)
    );

    for (let i = 0; i <= doc1.length; i++) {
        for (let j = 0; j <= doc2.length; j++) {
            if (i == 0) dp[i][j] = j; 
            else if (j == 0) dp[i][j] = i; 
            else if (doc1[i - 1] == doc2[j - 1]) dp[i][j] = dp[i - 1][j - 1];
            else
                dp[i][j] =
                    1 +
                    Math.min(
                        dp[i][j - 1], // Insert
                        dp[i - 1][j], // Remove
                        dp[i - 1][j - 1]
                    ); // Replace
        }
    }

    return dp[doc1.length][doc2.length];
}

module.exports = {
    findAllShiftsInDocs,
    minEditDistance,
    shiftDoc,
    tokeniser,
    stringFromTokens,
};


