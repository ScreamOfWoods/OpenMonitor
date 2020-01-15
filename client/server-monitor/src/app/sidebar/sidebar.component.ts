import { Component, OnInit, Output, EventEmitter } from '@angular/core';
import { View,NavigationService } from '../navigation.service';

@Component({
  selector: 'app-sidebar',
  templateUrl: './sidebar.component.html',
  styleUrls: ['./sidebar.component.css']
})
export class SidebarComponent implements OnInit {

  @Output() ViewChanged = new EventEmitter<View>();
  @Output() HostChanged = new EventEmitter<number>();

hosts = [
  {name:'host1', id:1},{name: 'host2', id:2}
]

  constructor(private navigation: NavigationService) { }

  ngOnInit() {
  }

  viewClick(viewId: number){
    console.log(viewId);
    switch(viewId)
    {
      case 1: {
        this.ViewChanged.emit(View.CPU);
        this.navigation.selectedView=View.CPU;
        break;
      }
      case 2: {
        this.ViewChanged.emit(View.Process);
        this.navigation.selectedView=View.Process;
        break;
      }
      case 3: {
        this.ViewChanged.emit(View.Memory);
        this.navigation.selectedView=View.Memory;
      break;
      }
      case 4: {
        this.ViewChanged.emit(View.General);
        this.navigation.selectedView=View.General;
      break;
      }
      default : {
        this.ViewChanged.emit(View.General);
        this.navigation.selectedView=View.General;
        break;
      }
    }
  }

  hostClick(hostId: number)
  {
    console.log(hostId);
      this.navigation.selectedHostId = hostId;
  }
}
