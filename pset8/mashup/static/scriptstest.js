var map;
var lakeside = {lat: 1.344368, lng: 103.720518};
function initMap() {
  map = new google.maps.Map(document.getElementById('map'), {
    center: lakeside,
    zoom: 12
  });
  var marker = new google.maps.Marker({
    position: lakeside,
    map: map
  });

  var contentString = '<div id="content">'+
    '<div id="siteNotice">'+
    '</div>'+
    '<h1 id="firstHeading" >Lakeside MRT</h1>'+
    '<div id="bodyContent">'+
    '<p><b>Lakeside MRT</b>, Lakeside MRT Station is an above-ground Mass Rapid Transit station on the East West Line in Jurong West, Singapore. Its station colour is red and green. </p>'+
    '<p>Attribution: Lakeside MRT <a href="https://en.wikipedia.org/wiki/Lakeside_MRT_Station">'+
    '</div>'+
    '</div>';

  var infowindow = new google.maps.InfoWindow({
  content: contentString
  });

  marker.addListener('click', function() {
  infowindow.open(map, marker);
  });
}