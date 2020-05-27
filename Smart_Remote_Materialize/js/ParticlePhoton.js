/*
Future research:
-importing a js file in another js file (for encapuslation purposes)
 */
var accessToken = "";
var deviceID = ""
var light_url = "https://api.particle.io/v1/devices/" + deviceID + "/led";
var receive_url = "https://api.particle.io/v1/devices/" + deviceID + "/receive";
var send_url = "https://api.particle.io/v1/devices/" + deviceID + "/send";

//light switch
function switchOn()
{
    $.post(light_url, {params: "on", access_token: accessToken });
}

function switchOff()
{
    $.post(light_url, {params: "off", access_token: accessToken });
}

//bug in JS, probably $(this).attr('id')
function buttonSelector(param)
{
    //var button = $(this).attr('id');
    var button = param.id;
    //test
    //alert(button);
    $.post(send_url, {params: button , access_token: accessToken });
    //window.alert(button);
}

function setup(param)
{
    //var status = this.id;
        //$(this).attr('id'); //make setup button id "true"
    var status = param.id;
    //alert(status);
    $.post(receive_url, {params: status , access_token: accessToken });
}

