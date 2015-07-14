Pebble.addEventListener('ready', function(event) {
  console.log("neat");
});

Pebble.addEventListener('showConfiguration', function(event) {
  Pebble.openURL('https://erisdev.github.io/pipboy-micro/settings.html');
});

Pebble.addEventListener('webviewclosed', function(event) {
  var config = JSON.parse(decodeURIComponent(event.response));
  console.debug(config);
//   Pebble.sendAppMessage(config, function() {
//     console.log("Settings are updated.");
//   }, function() {
//     console.error("There was a problem sending the settings over.");
//   });
});