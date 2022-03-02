import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import number
from esphome.const import (
    CONF_ADDRESS,
    CONF_ID,
    CONF_LAMBDA,
    CONF_MAX_VALUE,
    CONF_MIN_VALUE,
    CONF_STEP,
)
from .. import (
    ExtraflameComponent,
    extraflame_ns,
    EXTRAFLAME_COMPONENT_SCHEMA,
    get_memory_address,
)
from ..const import CONF_EXTRAFLAME_ID, CONF_MEMORY, CONF_WRITE_LAMBDA

DEPENDENCIES = ["extraflame"]
CODEOWNERS = ["@edenhaus"]

ExtraflameNumber = extraflame_ns.class_(
    "ExtraflameNumber", ExtraflameComponent, number.Number
)

CONFIG_SCHEMA = EXTRAFLAME_COMPONENT_SCHEMA.extend(
    number.NUMBER_SCHEMA.extend(
        {
            cv.GenerateID(): cv.declare_id(ExtraflameNumber),
            cv.Required(CONF_MAX_VALUE): cv.float_,
            cv.Required(CONF_MIN_VALUE): cv.float_,
            cv.Optional(CONF_STEP, default=1): cv.positive_float,
            cv.Optional(CONF_LAMBDA): cv.returning_lambda,
            cv.Optional(CONF_WRITE_LAMBDA): cv.returning_lambda,
        }
    )
)


async def to_code(config):
    var = cg.new_Pvariable(
        config[CONF_ID], get_memory_address(config[CONF_MEMORY]), config[CONF_ADDRESS]
    )
    await cg.register_component(var, config)
    await number.register_number(
        var,
        config,
        min_value=config[CONF_MIN_VALUE],
        max_value=config[CONF_MAX_VALUE],
        step=config[CONF_STEP],
    )
    await cg.register_parented(var, config[CONF_EXTRAFLAME_ID])

    if CONF_LAMBDA in config:
        template_ = await cg.process_lambda(
            config[CONF_LAMBDA],
            [(cg.uint8, "x")],
            return_type=cg.optional.template(float),
        )
        cg.add(var.set_template(template_))

    if CONF_WRITE_LAMBDA in config:
        template_ = await cg.process_lambda(
            config[CONF_WRITE_LAMBDA],
            [
                (cg.float_, "x"),
                (cg.uint8, "current_value"),
            ],
            return_type=cg.optional.template(cg.uint8),
        )
        cg.add(var.set_write_template(template_))
