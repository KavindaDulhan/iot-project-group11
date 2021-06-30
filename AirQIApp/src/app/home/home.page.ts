import { Component } from '@angular/core';
import { AQService } from './../services/aq.service';

@Component({
    selector: 'app-home',
    templateUrl: 'home.page.html',
    styleUrls: ['home.page.scss'],
})
export class HomePage {

    AQI: any;
    latitude: any;
    longitude: any;

    aqiColor: any;

    constructor(private AQ: AQService) { }

    ngOnInit() {
    }

    getAirQuality() {
        this.AQ.getAQI().subscribe((data: any[]) => {
            console.log(data);
            if (data["aqi"] <= 50) {
                this.aqiColor = "success"
            }
            else if (data["aqi"] <= 100) {
                this.aqiColor = "warning";
            }
            else {
                this.aqiColor = "danger"
            }
            this.AQI = data["aqi"];
        })
    }

    getLocation() {
        this.AQ.getLocation().subscribe((data: any[]) => {
            console.log(data);
            this.latitude = data["latitude"];
            this.longitude = data["longitude"]
        })
    }

    onButtonClick() {
        this.getAirQuality();
        this.getLocation();


    }
}
