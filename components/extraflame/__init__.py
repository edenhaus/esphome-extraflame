import esphome.codegen as cg
import esphome.config_validation as cv
from esphome import automation
from esphome.components import uart
from esphome.const import CONF_ID, CONF_ADDRESS, CONF_VALUE
from .const import CONF_MEMORY, MEMORY_RAM, MEMORY_EEPROM, CONF_EXTRAFLAME_ID

DEPENDENCIES = ["uart"]
CODEOWNERS = ["@edenhaus"]

extraflame_ns = cg.esphome_ns.namespace("extraflame")
ExtraflameHub = extraflame_ns.class_("ExtraflameHub", cg.Component, uart.UARTDevice)
ExtraflameComponent = extraflame_ns.class_("ExtraflameComponent", cg.PollingComponent)
ExtraflameWriteAction = extraflame_ns.class_("ExtraflameWriteAction", automation.Action)

EXTRAFLAME_COMPONENT_SCHEMA = cv.polling_component_schema("60s").extend({
    cv.GenerateID(CONF_EXTRAFLAME_ID): cv.use_id(ExtraflameHub),

    cv.Required(CONF_ADDRESS): cv.hex_uint8_t,
    cv.Required(CONF_MEMORY): cv.one_of(MEMORY_RAM, MEMORY_EEPROM, upper=True)
})

CONFIG_SCHEMA = (
    cv.Schema({
        cv.GenerateID(): cv.declare_id(ExtraflameHub),
    })
    .extend(cv.COMPONENT_SCHEMA)
    .extend(uart.UART_DEVICE_SCHEMA)
)


async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)
    await uart.register_uart_device(var, config)


@automation.register_action(
    "extraflame.write",
    ExtraflameWriteAction,
    cv.Schema(
        {
            cv.GenerateID(): cv.use_id(ExtraflameHub),
            cv.Required(CONF_MEMORY): cv.one_of(MEMORY_RAM, MEMORY_EEPROM, upper=True),
            cv.Required(CONF_ADDRESS): cv.templatable(cv.hex_uint8_t),
            cv.Required(CONF_VALUE): cv.templatable(cv.hex_uint8_t),
        }
    ),
)
async def extraflame_write_to_code(config, action_id, template_arg, args):
    var = cg.new_Pvariable(action_id, template_arg)
    await cg.register_parented(var, config[CONF_ID])

    template_ = await cg.templatable(config[CONF_ADDRESS], args, cg.uint8)
    cg.add(var.set_address(template_))
    template_ = await cg.templatable(config[CONF_VALUE], args, cg.uint8)
    cg.add(var.set_value(template_))
    cg.add(var.set_memory(config[CONF_MEMORY]))
    await var
