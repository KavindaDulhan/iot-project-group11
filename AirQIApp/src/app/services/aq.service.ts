import { HttpClient } from '@angular/common/http';
import { Injectable } from '@angular/core';

@Injectable({
    providedIn: 'root'
})
export class AQService {
    private ESP8266_SERVER = "http://esp8266.local"

    constructor(private http: HttpClient) { }

    getAQI() {
        return this.http.get(this.ESP8266_SERVER + "/aqi");
    }

    getLocation() {
        return this.http.get(this.ESP8266_SERVER + "/location")
    }

}
