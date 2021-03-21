# EspHome-Extraflame

Custom component for EspHome to control your extraflame oven

## 1. Installation

Create the folder `custom_components` (where the `config.yaml` is stored) if it is missing.
Clone this repository with the comment below:

```bash
git clone https://github.com/edenhaus/esphome-extraflame.git extraflame
```

## 2. Base Configuration

The base configuration is needed for all other components to work.
Copy the configuration below into your configuration file. For further options of uart please refer to the [docs](https://esphome.io/components/uart.html)

```yaml
uart:
  baud_rate: 1200
  # data_bits: 8
  # parity: NONE
  stop_bits: 2

extraflame:
```

### 2.1. Sensor

With a sensor it is possible to read any value from the RAM or EEPROM. It will be reported as decimal number.
The addresses seem to be different for different boards. A reference can be found [here](https://k3a.me/ir-controller-for-pellet-stove-with-micronova-controller-stufe-e-pellet-aria-ir-telecomando/)

Typical example of using this sensor would look like this:

```yaml
sensor:
  - platform: extraflame
    memory: RAM
    address: 0x01
```

Here is what every options means:

| Name       |     Type     | Default      | Description                 |
| ---------- | :----------: | ------------ | --------------------------- |
| `platform` |   `string`   | **Required** | `extraflame`                |
| `memory`   |   `string`   | **Required** | `RAM` or `EEPROM`           |
| `address`  | `hex number` | **Required** | The address as a hex number |

You can use in addition all [sensor options](https://esphome.io/components/sensor/index.html).
As for example the temperature must be divided by 2, below an complete example, where I use the built in filters.

```yaml
sensor:
  - platform: extraflame
    memory: RAM
    address: 0x01
    name: ${name} Temperatur
    filters:
      - multiply: 0.5
```

## 3. Roadmap

The next step is to support writes changes to the oven.
This component is at an early stage so please be aware that there can be bugs...

## 4. Author & License

Robert Resch, MIT, 2021
