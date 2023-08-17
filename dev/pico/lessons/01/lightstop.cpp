 if (light >= 3200) {      
                        // go photoresistor state
                        state = PHOTORESISTOR;
                        cout << "light val: " << light << "\n";
                        //i also have to reset the number for the photoresitor
                        break;
                    }
                }
            }
            break;
        case PHOTORESISTOR:
            cout << "photoresistor, brightest light is found\n";
            uint16_t light = adc_read();
            cout << "light val: " << light << "\n";
            sleep_ms(100);
            //if(light >= 3200) {
            state = STOP;
            //}
        }