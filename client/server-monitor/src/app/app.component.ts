import { Component } from '@angular/core';
import { NavigationService, View } from './navigation.service';
import { ServerService } from './server.service';

@Component({
  selector: 'app-root',
  templateUrl: './app.component.html',
  styleUrls: ['./app.component.css']
})
export class AppComponent {
  get view() { return View; }
  title = 'server-monitor';
  sidebarVisible: boolean;
  ngOnInit()
  {
    this.server.getHosts(null).then(responce=> {
        var res=(responce as any);
        console.log(res);
        this.navigation.hosts = res;
        this.navigation.selectedHostId = this.navigation.hosts[0].id;
        this.navigation.refreshData();
    },error=>{console.log("error: " + error)});
  }
  constructor(public navigation: NavigationService,private server: ServerService){

  }
  ToggleSidebar()
  {
    this.sidebarVisible = !this.sidebarVisible;
  }
  HideSidebar() {
    console.log("hide sidebar");
    this.sidebarVisible = false;
  }
}
