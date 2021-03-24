import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import sensor
from esphome.const import CONF_ADDRESS, CONF_ID
from .. import ExtraflameComponent, extraflame_ns, ExtraflameHub, EXTRAFLAME_COMPONENT_SCHEMA
from ..const import CONF_EXTRAFLAME_ID, CONF_MEMORY, MEMORY_RAM, MEMORY_EEPROM

DEPENDENCIES = ["extraflame"]
CODEOWNERS = ["@edenhaus"]

ExtraflameSensor = extraflame_ns.class_("ExtraflameSensor", ExtraflameComponent, sensor.Sensor)

CONFIG_SCHEMA = EXTRAFLAME_COMPONENT_SCHEMA.extend(sensor.SENSOR_SCHEMA.extend({
    cv.GenerateID(): cv.declare_id(ExtraflameSensor),
    cv.GenerateID(CONF_EXTRAFLAME_ID): cv.use_id(ExtraflameHub),

    cv.Required(CONF_ADDRESS): cv.hex_uint8_t,
    cv.Required(CONF_MEMORY): cv.one_of(MEMORY_RAM, MEMORY_EEPROM, upper=True)
}))


def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID], config[CONF_MEMORY], config[CONF_ADDRESS])
    yield cg.register_component(var, config)
    yield sensor.register_sensor(var, config)

    hub = yield cg.get_variable(config[CONF_EXTRAFLAME_ID])
    cg.add(var.set_extraflame_hub(hub))
