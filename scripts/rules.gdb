gdb ./bin/ELM327_app

# Establecer puntos de interrupción
break PNG::Png_t::open
break PNG::Png_t::decode
break PNG::Png_t::close

break RENDER::Render_t::Render_t
break RENDER::Render_t::init_display
break ST7789_DRV::St7789_t::init
break ST7789_DRV::St7789_t::clearScreen


# Ejecutar el programa
run

# Verificar si el archivo se abrió correctamente
print filePath
print file

# Continuar la ejecución hasta el próximo breakpoint
continue

# Inspeccionar las variables al decodificar la imagen PNG
print image_width
print image_height
print in_size

# Ver el contenido del buffer PNG cargado
x/10xb in_png_binary.data()

# Finalizar la depuración
quit