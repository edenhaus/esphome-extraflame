import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.const import CONF_ID
from esphome.components import http_request
from ..extraflame.const import  CONF_EXTRAFLAME_ID
from ..extraflame import ExtraflameHub

DEPENDENCIES = ["extraflame", "api"] #, "http_request"]
CODEOWNERS = ["@edenhaus"]

extraflame_ns = cg.esphome_ns.namespace("extraflame")
ExtraflameDump = extraflame_ns.class_("ExtraflameDump", cg.Component)

_CONF_HTTP_REQUEST_ID = "http_request_id"

CONFIG_SCHEMA = cv.Schema({
        cv.GenerateID(): cv.declare_id(ExtraflameDump),
        cv.GenerateID(CONF_EXTRAFLAME_ID): cv.use_id(ExtraflameHub),
        #cv.GenerateID(_CONF_HTTP_REQUEST_ID): cv.use_id(http_request.HttpRequestComponent),
   })


async def to_code(config):
    #http_request = await cg.get_variable(config[_CONF_HTTP_REQUEST_ID])
    var = cg.new_Pvariable(config[CONF_ID]) #, http_request)
    await cg.register_component(var, config)
    await cg.register_parented(var, config[CONF_EXTRAFLAME_ID])
