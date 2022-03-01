import esphome.codegen as cg
import esphome.config_validation as cv
from esphome import automation
from esphome.automation import Condition, maybe_simple_id, Action, Trigger
from esphome.components import uart
from esphome.const import CONF_ID, CONF_ADDRESS, CONF_VALUE, CONF_TRIGGER_ID
from .const import (
    CONF_MEMORY,
    MEMORY_ADDRESSES,
    CONF_EXTRAFLAME_ID,
    CONF_ON_DUMP_FINISH,
    CONF_START,
    CONF_END
)

DEPENDENCIES = ["uart"]
CODEOWNERS = ["@edenhaus"]

extraflame_ns = cg.esphome_ns.namespace("extraflame")
ExtraflameHub = extraflame_ns.class_("ExtraflameHub", cg.Component, uart.UARTDevice)
ExtraflameComponent = extraflame_ns.class_("ExtraflameComponent", cg.PollingComponent)
ExtraflameWriteAction = extraflame_ns.class_("ExtraflameWriteAction", Action)
ExtraflameDumpAction = extraflame_ns.class_("ExtraflameDumpAction", Action)
ExtraflameDumpFinishTrigger = extraflame_ns.class_(
    "ExtraflameDumpFinishTrigger", Trigger.template(cg.std_string)
)
ExtraflameIsDumpingCondition = extraflame_ns.class_("ExtraflameIsDumpingCondition", Condition)

is_memory_address = cv.Any(
    cv.one_of(*MEMORY_ADDRESSES, upper=True),
    cv.All(
        cv.hex_int,
        cv.one_of(*[v for k, v in MEMORY_ADDRESSES.items()], int=True),
    ),
)

EXTRAFLAME_COMPONENT_SCHEMA = cv.polling_component_schema("60s").extend(
    {
        cv.GenerateID(CONF_EXTRAFLAME_ID): cv.use_id(ExtraflameHub),
        cv.Required(CONF_ADDRESS): cv.hex_uint8_t,
        cv.Required(CONF_MEMORY): is_memory_address,
    }
)


CONFIG_SCHEMA = (
    cv.Schema(
        {
            cv.GenerateID(): cv.declare_id(ExtraflameHub),
        }
    )
    .extend(cv.COMPONENT_SCHEMA)
    .extend(uart.UART_DEVICE_SCHEMA)
)


def get_memory_address(value):
    if isinstance(value, int):
        return value

    return MEMORY_ADDRESSES[value]


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
            cv.Required(CONF_MEMORY): is_memory_address,
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
    cg.add(var.set_memory(get_memory_address(config[CONF_MEMORY])))
    return var

@automation.register_action(
    "extraflame.dump",
    ExtraflameDumpAction,
    cv.Schema(
        {
            cv.GenerateID(): cv.use_id(ExtraflameHub),
            cv.Required(CONF_MEMORY): is_memory_address,
            cv.Required(CONF_START): cv.templatable(cv.hex_uint8_t),
            cv.Required(CONF_END): cv.templatable(cv.hex_uint8_t),
            cv.Required(CONF_ON_DUMP_FINISH): automation.validate_automation(
                {
                    cv.GenerateID(CONF_TRIGGER_ID): cv.declare_id(
                        ExtraflameDumpFinishTrigger
                    ),
                }
            ),
        }
    ),
)
async def extraflame_dump_to_code(config, action_id, template_arg, args):
    if CONF_ON_DUMP_FINISH in config:
        cg.add_define("USE_EXTRAFLAME_DUMP")

    var = cg.new_Pvariable(action_id, template_arg)
    await cg.register_parented(var, config[CONF_ID])

    template_ = await cg.templatable(config[CONF_START], args, cg.uint8)
    cg.add(var.set_start(template_))
    template_ = await cg.templatable(config[CONF_END], args, cg.uint8)
    cg.add(var.set_end(template_))
    cg.add(var.set_memory(get_memory_address(config[CONF_MEMORY])))

    for conf in config.get(CONF_ON_DUMP_FINISH, []):
        trigger = cg.new_Pvariable(conf[CONF_TRIGGER_ID])
        cg.add(var.register_finish_trigger(trigger))
        await automation.build_automation(trigger, [(cg.std_string, "data")], conf)

    return var


@automation.register_condition(
    "extraflame.is_dumping", ExtraflameIsDumpingCondition, maybe_simple_id(
    {
        cv.GenerateID(): cv.use_id(ExtraflameHub),
    })
)
async def extraflame_is_dumping_to_code(config, condition_id, template_arg, args):
    cg.add_define("USE_EXTRAFLAME_DUMP")
    var = cg.new_Pvariable(condition_id, template_arg)
    await cg.register_parented(var, config[CONF_ID])
    return var
