// else if (String(topic) == "entc/group11/project/timezone"){
//   zone_hour[0] = (char)payload[1];
//   zone_hour[1] = (char)payload[2];
//   zone_minute[0] = (char)payload[4];
//   zone_minute[1] = (char)payload[5];
//   if ((char)payload[0]=='+'){
//     utcOffsetInSeconds = (String(zone_hour).toInt())*60*60 + (String(zone_minute).toInt())*60;
//   }
//   else if ((char)payload[0]=='-'){
//     utcOffsetInSeconds = ((String(zone_hour).toInt())*60*60 + (String(zone_minute).toInt())*60)*(-1);

//     char zone_hour[5];
// char zone_minute[5];
// long utcOffsetInSeconds = 19800;
// char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
// int time_hour;
// int time_minute;
// int time_second;
// long sleep_time;

// // Define NTP Client to get time
// WiFiUDP ntpUDP;
// NTPClient timeClient(ntpUDP, "pool.ntp.org", utcOffsetInSeconds);
