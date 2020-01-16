import { Injectable, EventEmitter } from '@angular/core';
import { ServerService } from './server.service';

@Injectable({
  providedIn: 'root'
})
export class NavigationService {
  currentDataChange: EventEmitter<any> = new EventEmitter();
  selectedHostId: number;
  selectedView = View.General;
  hosts: any;
  currentData: any={};
  clockData = [
    {
      "name": "Germany",
      "series": [
        {
          "name": "2010",
          "value": 7300000
        },
        {
          "name": "2011",
          "value": 8940000
        }
      ]
    }
  ];
  getNavChangeEmitter() {
    return this.currentDataChange;
  }
  constructor(private server: ServerService) { }

  refreshData()
  {
    switch(this.selectedView)
    {
      case View.General: {
          this.server.general(this.selectedHostId
          ).then(responce=> {
            var res=(responce as any);
            this.currentData = res;
            let boot= new Date(0);
            boot.setUTCSeconds(this.currentData.boot_time);
            this.currentData.boot_time = boot.toLocaleString();
            console.log(res);
        },error=>{console.log("error: " + error)});
        break;
      }
      case View.CPU: {
          this.server.cpu(this.selectedHostId
          ).then(responce=> {
            var res=(responce as any);
            this.clockData = res;
            this.currentDataChange.emit(res);
            console.warn(responce);
        },error=>{console.warn("error: " + error)});
        break;
      }
      case View.Memory: {
        this.server.general(this.selectedHostId
          ).then(responce=> {
            var res=(responce as any);
            this.currentData = res;
            console.log(res);
        },error=>{console.log("error: " + error)});
        break;
      }
      case View.Process: 
      {
        this.server.general(this.selectedHostId
        ).then(responce=> {
          var res=(responce as any);
          this.currentData = res;
          console.log(res);
        },error=>{console.log("error: " + error)});
        break;
      }
    }
  }
}
export enum View {
  General,
  CPU,
  Memory,
  Process
}