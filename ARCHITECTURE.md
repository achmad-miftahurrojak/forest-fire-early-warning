# Architecture

```text
Node 1: DHT22 + MQ-2 + soil sensor
                 |
                 v
              LoRa radio
                 |
                 v
Hub: LoRa receiver -> payload validation -> risk rule
                                      /          \
                                     v            v
                                  buzzer       SIM800L SMS
```

Each node samples environmental sensors, sends a structured CSV payload over LoRa, and enters deep sleep. The hub validates packet structure and value ranges before evaluating the fire risk rule. This implementation is a node-to-hub topology; it does not implement multi-hop mesh routing.
