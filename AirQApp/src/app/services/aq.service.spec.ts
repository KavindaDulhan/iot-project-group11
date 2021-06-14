import { TestBed } from '@angular/core/testing';

import { AQService } from './aq.service';

describe('AQService', () => {
  let service: AQService;

  beforeEach(() => {
    TestBed.configureTestingModule({});
    service = TestBed.inject(AQService);
  });

  it('should be created', () => {
    expect(service).toBeTruthy();
  });
});
