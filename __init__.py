import esphome.codegen as cg
import esphome.core as core
import esphome.config_validation as cv
from esphome.components import uart
from esphome.const import CONF_ID, CONF_UART_ID, CONF_DUMP

DEPENDENCIES = ["uart"]
CODEOWNERS = ["@edenhaus"]

extraflame_ns = cg.esphome_ns.namespace("extraflame")
ExtraflameHub = extraflame_ns.class_("ExtraflameHub", cg.Component, uart.UARTDevice)
ExtraflameComponent = extraflame_ns.class_("ExtraflameComponent", cg.PollingComponent)

EXTRAFLAME_COMPONENT_SCHEMA = cv.polling_component_schema("60s")


CONFIG_SCHEMA = (
    cv.Schema(
        {
            cv.GenerateID(): cv.declare_id(ExtraflameHub),
            cv.Optional(CONF_DUMP, default=False): cv.boolean,
        }
    )
    .extend(cv.COMPONENT_SCHEMA)
    .extend(uart.UART_DEVICE_SCHEMA)
)


def to_code(config):
    if config[CONF_DUMP]:
        DEPENDENCIES.append("api")
        cg.add_define("USE_EXTRAFLAME_DUMP")

    var = cg.new_Pvariable(config[CONF_ID])
    yield cg.register_component(var, config)
    yield uart.register_uart_device(var, config)
