import { Injectable } from '@angular/core';

@Injectable({
  providedIn: 'root'
})
export class NavigationService {
  selectedHostId: number;
  selectedView = View.General;
  constructor() { }
}
export enum View {
  General,
  CPU,
  Memory,
  Process
}