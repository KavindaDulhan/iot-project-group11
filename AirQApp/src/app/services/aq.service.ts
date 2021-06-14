import { HttpClient } from '@angular/common/http';
import { Injectable } from '@angular/core';

@Injectable({
    providedIn: 'root'
})
export class AQService {
    private ESP8266_SERVER = "http://192.168.8.105"

    constructor(private http: HttpClient) { }

    getAQI() {
        return this.http.get(this.ESP8266_SERVER + "/helloWorld");
    }

}
