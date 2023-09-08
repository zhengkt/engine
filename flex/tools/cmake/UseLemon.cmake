# use lemon generat gramer.c and gramer.h ... 
MACRO(ADD_LEMON_FILES SOURCE GENERATED)
    set(LEMON_PARSER_DIR ${CMAKE_CURRENT_SOURCE_DIR}/tools/lemon)
    FOREACH (CURRENT_FILE ${ARGN})
      GET_FILENAME_COMPONENT(IN ${CURRENT_FILE} ABSOLUTE)
      GET_FILENAME_COMPONENT(BASE_NAME ${CURRENT_FILE} NAME_WE)

      SET(OUT ${CMAKE_CURRENT_BINARY_DIR}/${BASE_NAME})

      ADD_CUSTOM_COMMAND(
         OUTPUT
          ${OUT}.c
          ${OUT}.h
          ${OUT}.out
         COMMAND $<TARGET_FILE:lemon>
           -T${LEMON_PARSER_DIR}/lempar.c
           -d.
           ${IN} && ${CMAKE_CURRENT_SOURCE_DIR}/tools/lemon/commaline.sh ${_out}.c && ${CMAKE_CURRENT_SOURCE_DIR}/tools/lemon/commaline.sh ${_out}.h\;
         DEPENDS
           ${IN}
           lemon
           ${LEMON_PARSER_DIR}/lempar.c
      )
      LIST(APPEND ${SOURCE} ${IN})
      LIST(APPEND ${GENERATED} ${OUT}.c)
   ENDFOREACH (CURRENT_FILE)
ENDMACRO(ADD_LEMON_FILES)
