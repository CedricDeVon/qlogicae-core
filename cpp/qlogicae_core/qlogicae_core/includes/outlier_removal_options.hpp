#pragma once

namespace QLogicaeCore
{
    struct OutlierRemovalOptions
    {
        double factor;
        
        double threshold;
        
        double proportion;

        double significance_level;
    };
}
