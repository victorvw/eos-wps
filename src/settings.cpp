// @action
void wps::init( eosio::time_point_sec initial_voting_period )
{
    require_auth( get_self() );
    const eosio::name ram_payer = get_self();

    // check( !_state.exists(), "already initialized" );
    check( _settings.exists(), "settings are missing" );

    auto state = _state.get_or_default();
    auto settings = _settings.get();

    state.current_voting_period = initial_voting_period;
    state.next_voting_period = initial_voting_period + settings.voting_interval;

    _state.set( state, ram_payer );
    _settings.set( settings, ram_payer );

    // push deferred transaction using `next_voting_period` as the delay
    auto_complete();
}

// @action
void wps::setparams( const wps_parameters params )
{
    require_auth( get_self() );
    const eosio::name ram_payer = get_self();

    _settings.set( params, ram_payer );
}

void wps::add_funding( const eosio::asset quantity )
{
    const eosio::name ram_payer = get_self();

    auto state = _state.get();
    state.available_funding += quantity;
    _state.set( state, ram_payer );
}

void wps::sub_funding( const eosio::asset quantity )
{
    const eosio::name ram_payer = get_self();

    auto state = _state.get();
    state.available_funding -= quantity;
    _state.set( state, ram_payer );
}
