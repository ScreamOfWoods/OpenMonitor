import {Component, NgModule,OnInit} from '@angular/core';
import { NavigationService } from '../navigation.service';

@Component({
  selector: 'app-cpu-info',
  templateUrl: './cpu-info.component.html',
  styleUrls: ['./cpu-info.component.css']
})
export class CpuInfoComponent implements OnInit {

  subs: any;
  constructor(private navigation: NavigationService){}

  ngOnInit() {
    this.subs = this.navigation.getNavChangeEmitter().subscribe(item => this.setData(item));
      console.log(this.data); 
  }
  setData(newData:any)
  {
    this.data = newData;
  }
  
  data = [
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
  //data = [{"name":"Intel(R) Core(TM) i7-7700HQ CPU @ 2.80GHz","series":[{"name":8,"value":2373.98475},{"name":16,"value":1636.8700000000003},{"name":24,"value":2024.6213750000006},{"name":32,"value":2195.236968750001},{"name":40,"value":2082.1210750000005},{"name":48,"value":2202.015833333334},{"name":56,"value":2287.0026071428574}]}];

  // options
  showXAxis = true;
  showYAxis = true;
  gradient = false;
  showLegend = true;
  showXAxisLabel = true;
  xAxisLabel = 'Time';
  showYAxisLabel = true;
  yAxisLabel = 'Clock';

  colorScheme = {
    domain: ['#5AA454', '#A10A28', '#C7B42C', '#AAAAAA']
  };

  // line, area
  autoScale = true;

  
  onSelect(event) {
    console.log(event);
  }
  
}