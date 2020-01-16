import { Injectable } from '@angular/core';
import { ServerService } from './server.service';

@Injectable({
  providedIn: 'root'
})
export class NavigationService {
  selectedHostId: number;
  selectedView = View.General;
  hosts: any;
  currentData: any={};
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
          this.server.general(this.selectedHostId
          ).then(responce=> {
            var res=(responce as any);
            this.currentData = res;
            console.log(res);
        },error=>{console.log("error: " + error)});
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