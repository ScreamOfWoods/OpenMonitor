import { Component, OnInit } from '@angular/core';
import { ServerService } from '../server.service';
import { NavigationService } from '../navigation.service';

@Component({
  selector: 'app-general-info',
  templateUrl: './general-info.component.html',
  styleUrls: ['./general-info.component.css']
})
export class GeneralInfoComponent implements OnInit {

  constructor(private server: ServerService,public navigation: NavigationService) { }

  ngOnInit() {
    /*this.server.getChats(
      {

      }
      ).then(responce=> {
        var res=(responce as any);
        console.log(res);
    },error=>{console.log("error: " + error)});*/
  }

}
