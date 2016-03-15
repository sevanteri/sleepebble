function sendMessage() {
    Pebble.sendAppMessage({"status": 1}, messageSuccessHandler, messageFailureHandler);
}

// Called when the message send attempt succeeds
function messageSuccessHandler() {
    console.log("Message send succeeded.");  
}

// Called when the message send attempt fails
function messageFailureHandler() {
    console.log("Message send failed.");
    sendMessage();
}

// Called when JS is ready
Pebble.addEventListener("ready", function(e) {
    console.log("JS is ready!");
    //sendMessage();
});

// Called when incoming message from the Pebble is received
// We are currently only checking the "message" appKey defined in appinfo.json/Settings
Pebble.addEventListener("appmessage", function(e) {
    console.log("Received Message: " + e.payload.message);
});

Pebble.addEventListener('showConfiguration', function() {
  var url = 'https://raw.githubusercontent.com/sevanteri/sleepebble/master/config/config.html';

  Pebble.openURL(url);
});
