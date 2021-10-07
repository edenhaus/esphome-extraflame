import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import sensor
from esphome.const import CONF_ADDRESS, CONF_ID
from .. import ExtraflameComponent, extraflame_ns, EXTRAFLAME_COMPONENT_SCHEMA
from ..const import CONF_EXTRAFLAME_ID, CONF_MEMORY

DEPENDENCIES = ["extraflame"]
CODEOWNERS = ["@edenhaus"]

ExtraflameSensor = extraflame_ns.class_("ExtraflameSensor", ExtraflameComponent, sensor.Sensor)

CONFIG_SCHEMA = EXTRAFLAME_COMPONENT_SCHEMA.extend(
    sensor.SENSOR_SCHEMA.extend({
        cv.GenerateID(): cv.declare_id(ExtraflameSensor),
    })
)


async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID], config[CONF_MEMORY], config[CONF_ADDRESS])
    await cg.register_component(var, config)
    await sensor.register_sensor(var, config)
    await cg.register_parented(var, config[CONF_EXTRAFLAME_ID])
