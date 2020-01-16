import { BrowserModule } from '@angular/platform-browser';
import { NgModule } from '@angular/core';
import { HttpClientModule } from '@angular/common/http';

import { AppRoutingModule } from './app-routing.module';
import { AppComponent } from './app.component';
import { SidebarComponent } from './sidebar/sidebar.component';
import { GeneralInfoComponent } from './general-info/general-info.component';
import { CpuInfoComponent } from './cpu-info/cpu-info.component';
import { MemoryInfoComponent } from './memory-info/memory-info.component';
import { ProcessInfoComponent } from './process-info/process-info.component';
import { NgxChartsModule } from '@swimlane/ngx-charts';
import { BrowserAnimationsModule } from '@angular/platform-browser/animations';

@NgModule({
  declarations: [
    AppComponent,
    SidebarComponent,
    GeneralInfoComponent,
    CpuInfoComponent,
    MemoryInfoComponent,
    ProcessInfoComponent
  ],
  imports: [
    BrowserModule,
    HttpClientModule,
    AppRoutingModule,
    BrowserAnimationsModule,
    NgxChartsModule 
  ],
  providers: [],
  bootstrap: [AppComponent]
})
export class AppModule { }
