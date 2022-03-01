# EspHome-Extraflame

Custom component for EspHome to control your extraflame oven.

**I will not anwser to mails, written about this project!! A issue can be read from anyone and a mail is only between two people.**

I will describe here only the software part. The wiring with the board can be done in different ways. Some are described [here](https://k3a.me/ir-controller-for-pellet-stove-with-micronova-controller-stufe-e-pellet-aria-ir-telecomando/)

## 1. Installation

Please add the following snippet into your configuration file.
More information about `external_components` can be found in the official [docs](https://esphome.io/components/external_components.html)

```yaml
external_components:
  - source: github://edenhaus/esphome-extraflame
    components: [extraflame]
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

| Name       |      Type       | Default      | Description                 |
| ---------- | :-------------: | ------------ | --------------------------- |
| `platform` | `static string` | **Required** | `extraflame`                |
| `memory`   |    `string`     | **Required** | `RAM` or `EEPROM`           |
| `address`  |  `hex number`   | **Required** | The address as a hex number |

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

## 3. Write a value

Writing a value can be done with the following action:

```yaml
extraflame.write:
  memory: RAM
  address: 0x21
  value: 0x01
```

Here is what every options means:

| Name      |     Type     | Default      | Description                               |
| --------- | :----------: | ------------ | ----------------------------------------- |
| `memory`  |   `string`   | **Required** | `RAM` or `EEPROM`                         |
| `address` | `hex number` | **Required** | The address as a hex number               |
| `value`   | `hex number` | **Required** | The actual value, which you want to write |

All fields can be used with template and lambdas. More information about action can be found in the official [documentation](https://esphome.io/guides/automations.html).
Before writing the value to the memory, a read request is send to verify if a write command is necessary. This should reduce unnecessary write as the EEPROM can has only a certain number of writes.

## 4. Dumping values

As different oven, stores the interesting data on different addresses, we need a way to dump all or certain values.
To use the "dumping" as flexable as possible, dumping is an action. More information about action and automation can be found [here](https://esphome.io/guides/automations.html).


```yaml
- extraflame.dump:
    memory: RAM
    start: 0x00
    end: 0xFF
    on_dump_finish:
      then:
        - http_request.send:
            method: POST
            url: your_URL
            headers:
              Content-Type: application/json
            body: !lambda return data.c_str();
```

Here is what every options means:

| Name             |      Type      | Default      | Description                                                                                                               |
|------------------|:--------------:| ------------ |---------------------------------------------------------------------------------------------------------------------------|
| `memory`         |    `string`    | **Required** | `RAM` or `EEPROM`                                                                                                         |
| `start`          | `(hex) number` | **Required** | From which address the values are dumped. Values must be between 0x0 - 0xFF (255)                                         |
| `end`            | `(hex) number` | **Required** | Until which address the values are dumped. Values must be between 0x0 - 0xFF (255)                                        |
| `on_dump_finish` |  `Automation`  | **Required** | An automation to perform when the dumping is finished. The dumped values are passed as json string variable named `data`. |

Please check out the [example](example.yaml) for a complete example.

## 5. Roadmap

This component is at an early stage so please be aware that there can be bugs...

## 6. Author & License

Robert Resch, MIT, 2021
