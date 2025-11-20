function pressKey(value) {
    document.getElementById("display").value += value;
}

function clearDisplay() {
    document.getElementById("display").value = "";
}

function calculate() {
    let exp = document.getElementById("display").value;

    exp = exp.replace(/\^/g, "**"); // for power

    try {
        document.getElementById("display").value = eval(exp);
    } catch {
        document.getElementById("display").value = "Error";
    }
}

/* -------- THEME SWITCH CODE -------- */
function changeTheme() {
    const theme = document.getElementById("themeSelector").value;
    document.body.className = theme;
}
