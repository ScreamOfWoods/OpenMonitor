import { Component } from '@angular/core';
import { NavigationService, View } from './navigation.service';

@Component({
  selector: 'app-root',
  templateUrl: './app.component.html',
  styleUrls: ['./app.component.css']
})
export class AppComponent {
  get view() { return View; }
  title = 'server-monitor';
  sidebarVisible: boolean;
  constructor(public navigation: NavigationService){

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
