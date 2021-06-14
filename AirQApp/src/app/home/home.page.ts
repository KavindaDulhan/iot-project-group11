import { Component } from '@angular/core';
import { AQService } from './../services/aq.service';

@Component({
    selector: 'app-home',
    templateUrl: 'home.page.html',
    styleUrls: ['home.page.scss'],
})
export class HomePage {

    AQI: any;

    constructor(private AQ: AQService) { }

    ngOnInit() {
    }

    getAirQuality() {
        this.AQ.getAQI().subscribe((data: any[]) => {
            console.log(data);
            this.AQI = data["aqi"];
        })
    }
}
