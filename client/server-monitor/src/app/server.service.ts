import { Injectable } from '@angular/core';
import { environment } from 'src/environments/environment';

import { HttpClient, HttpParams } from '@angular/common/http';

@Injectable({
  providedIn: 'root'
})
export class ServerService {

  constructor(private http: HttpClient) {
  }

  private async request(method: string, url: string, data?: any, parameters?:any) {
    const result = this.http.request(method, url, {
      body: data,
      params: parameters,
      responseType: 'json',
      observe: 'body',
      headers: {
        Authorization: 'Bearer'
      }
    });
    return new Promise((resolve, reject) => {
      result.subscribe(resolve, reject);
    });
  }

  getHosts(parameters) {
    return this.request('GET', `${environment.serverUrl}/hosts`, null, parameters);
  }

  general(parameters) {
    return this.request('GET', `${environment.serverUrl}/general/`+parameters);
  }

  cpu(parameters) {
    return this.request('GET', `${environment.serverUrl}/cpu/clock/`+parameters);
  }

  createUser(event) {
    return this.request('POST', `${environment.serverUrl}/createUser`, event);
  }
}