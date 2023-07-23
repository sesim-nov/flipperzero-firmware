#include <furi_hal_region.h>
#include <furi_hal_version.h>
#include <furi.h>

const FuriHalRegion furi_hal_region_zero = {
    .country_code = "OK",
    .bands_count = 3,
    .bands = {
        {

            .end = 300000000,
            .power_limit = 12,
            .duty_cycle = 50,
        },
        {
            .start = 433050000,
            .end = 434790000,
            .power_limit = 12,
            .duty_cycle = 50,
        },
        {
            .start = 915000000,
            .end = 928000000,
            .power_limit = 12,
            .duty_cycle = 50,
        }}};

static const FuriHalRegion* furi_hal_region = NULL;

void furi_hal_region_init() {
    furi_hal_region = &furi_hal_region_zero;
}

const FuriHalRegion* furi_hal_region_get() {
    return furi_hal_region;
}

void furi_hal_region_set(FuriHalRegion* region) {
    UNUSED(region);
    furi_hal_region = &furi_hal_region_zero;
}

bool furi_hal_region_is_provisioned() {
    return furi_hal_region != NULL;
}

const char* furi_hal_region_get_name() {
    if(furi_hal_region) {
        return furi_hal_region->country_code;
    } else {
        return "--";
    }
}

bool furi_hal_region_is_frequency_allowed(uint32_t frequency) {
    if(!furi_hal_region) {
        return false;
    }

    const FuriHalRegionBand* band = furi_hal_region_get_band(frequency);
    if(!band) {
        return false;
    }

    return true;
}

const FuriHalRegionBand* furi_hal_region_get_band(uint32_t frequency) {
    if(!furi_hal_region) {
        return NULL;
    }

    for(size_t i = 0; i < furi_hal_region->bands_count; i++) {
        if(furi_hal_region->bands[i].start <= frequency &&
           furi_hal_region->bands[i].end >= frequency) {
            return &furi_hal_region->bands[i];
        }
    }

    return NULL;
}
