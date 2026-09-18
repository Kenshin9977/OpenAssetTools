#pragma once

#include "Dumping/AssetDumpingContext.h"
#include "Dumping/IAssetDumper.h"

#include <memory>
#include <vector>

class IObjWriter
{
public:
    IObjWriter() = default;
    virtual ~IObjWriter() = default;
    IObjWriter(const IObjWriter& other) = default;
    IObjWriter(IObjWriter&& other) noexcept = default;
    IObjWriter& operator=(const IObjWriter& other) = default;
    IObjWriter& operator=(IObjWriter&& other) noexcept = default;

    bool DumpZone(AssetDumpingContext& context);

    // Which asset types this game's writer can actually dump. Registering the dumpers is the only
    // source of truth for that (the set differs per game and grows over time), so callers asking
    // "is type X covered" get an answer from the code rather than from a hand-kept list.
    [[nodiscard]] std::vector<asset_type_t> HandledAssetTypes(AssetDumpingContext& context);

    static IObjWriter* GetObjWriterForGame(GameId game);

protected:
    virtual void RegisterAssetDumpers(AssetDumpingContext& context) = 0;
    void RegisterAssetDumper(std::unique_ptr<IAssetDumper> dumper);

private:
    std::vector<std::unique_ptr<IAssetDumper>> m_asset_dumpers;
};
