import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.const import CONF_ID
from ..extraflame.const import  CONF_EXTRAFLAME_ID
from ..extraflame import ExtraflameHub

DEPENDENCIES = ["extraflame", "api", "http_request"]
AUTO_LOAD = ["json"]
CODEOWNERS = ["@edenhaus"]

extraflame_ns = cg.esphome_ns.namespace("extraflame")
ExtraflameDump = extraflame_ns.class_("ExtraflameDump", cg.Component)


CONFIG_SCHEMA = {
        cv.GenerateID(): cv.declare_id(ExtraflameDump),
        cv.GenerateID(CONF_EXTRAFLAME_ID): cv.use_id(ExtraflameHub),
   }


async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)
    await cg.register_parented(var, config[CONF_EXTRAFLAME_ID])
