function sendRequest(id) {
    var xhr = new XMLHttpRequest();

    xhr.open("DELETE", "/", true);

    xhr.setRequestHeader("Content-Type", "application/json");

    xhr.onloadend = function () {
        var json = JSON.parse(xhr.responseText);

        if (json["success"]) {
            window.location.href = "/";
        }
        else {
            alert("{% print($error$); %}");
            window.location.href = "/";
        }
    };

    xhr.send(JSON.stringify({ "id": id }));
}
