# Edit following two lines to set component requirements (see docs)
set(COMPONENT_REQUIRES )
set(COMPONENT_PRIV_REQUIRES )

set(COMPONENT_SRCS "main.c" "circular_buffer.c" "potentiometer.c" "uart_remote.c" "bluetooth.c" "button.c")
set(COMPONENT_ADD_INCLUDEDIRS "")

register_component()
